TARGET = portfolio
SRC = main.cpp
INSTALL_PATH = /home/portfolio/bin/portfolio

$(TARGET): $(SRC)
	g++ $(SRC) -o $(TARGET)

deploy: $(TARGET)
	sudo cp $(TARGET) $(INSTALL_PATH)
	sudo chown portfolio:portfolio $(INSTALL_PATH)
	sudo chmod +x $(INSTALL_PATH)
	@echo "Deployed to $(INSTALL_PATH)"

clean:
	rm -f $(TARGET)

.PHONY: deploy clean
