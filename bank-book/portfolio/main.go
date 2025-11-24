package main

import (
	"context"
	"errors"
	"net"
	"os"
	"os/exec"
	"os/signal"
	"syscall"
	"time"

	"github.com/charmbracelet/log"
	"github.com/charmbracelet/ssh"
	"github.com/charmbracelet/wish"
	"github.com/charmbracelet/wish/activeterm"
	"github.com/charmbracelet/wish/logging"
	"github.com/charmbracelet/wish/recover"
)

const host = "0.0.0.0"

var port = func() string {
	if p := os.Getenv("PORT"); p != "" {
		return p
	}
	return "22" 
}()

func programHandler(path string) ssh.Handler {
	return func(s ssh.Session) {
		cmd := exec.Command(path)
		cmd.Stdout = s
		cmd.Stderr = s
		cmd.Stdin = s

		env := os.Environ()
		for _, e := range s.Environ() {
			env = append(env, e)
		}
		cmd.Env = env

		_ = cmd.Run() 
	}
}

func programMiddleware(path string) wish.Middleware {
	return func(next ssh.Handler) ssh.Handler {
		return programHandler(path)
	}
}


func main() {
	s, err := wish.NewServer(
		wish.WithAddress(net.JoinHostPort(host, port)),
		wish.WithHostKeyPath(".ssh/id_ed25519"),
		wish.WithMiddleware(
			recover.Middleware(
				programMiddleware("/home/public/portfolio"), 
				activeterm.Middleware(),
				logging.Middleware(),
			),
		),
	)

	if err != nil {
		log.Error("Could not create server", "error", err)
		os.Exit(1)
	}

	done := make(chan os.Signal, 1)
	signal.Notify(done, os.Interrupt, syscall.SIGINT, syscall.SIGTERM)

	log.Info("Starting SSH server", "host", host, "port", port)

	go func() {
		if err := s.ListenAndServe(); err != nil && !errors.Is(err, ssh.ErrServerClosed) {
			log.Error("Server error", "error", err)
			done <- nil
		}
	}()

	<-done
	log.Info("Stopping SSH server")

	ctx, cancel := context.WithTimeout(context.Background(), 30*time.Second)
	defer cancel()

	if err := s.Shutdown(ctx); err != nil && !errors.Is(err, ssh.ErrServerClosed) {
		log.Error("Failed to stop server cleanly", "error", err)
	}
}
