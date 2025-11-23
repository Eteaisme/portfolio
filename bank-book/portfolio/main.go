package main

import (
    "os"
    "os/exec"

    "github.com/charmbracelet/wish"
    "github.com/gliderlabs/ssh"
    "log"
)

func main() {
    s, err := wish.NewServer(
        wish.WithAddress(":22"),
        wish.WithHostKeyPath("ssh_host_key"),
        wish.WithMiddleware(func(next ssh.Handler) ssh.Handler {
            return func(sesh ssh.Session) {
                cmd := exec.Command("/~") 
                cmd.Stdin = sesh
                cmd.Stdout = sesh
                cmd.Stderr = sesh
                cmd.Run()
            }
        }),
    )

    if err != nil {
        log.Fatalf("error creating server: %v", err)
    }

    log.Printf("Starting SSH server on :22")
    if err := s.ListenAndServe(); err != nil {
        log.Fatalf("server closed: %v", err)
    }
}
