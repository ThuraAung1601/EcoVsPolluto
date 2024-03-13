#!/bin/bash

SFML_VERSION="2.6.1"
SFML_INSTALL_PATH="/usr/local"

echo "Installing SFML..."

# Install SFML using package manager
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    # For Debian-based systems (e.g., Ubuntu)
    sudo apt update
    sudo apt install libsfml-dev
elif [[ "$OSTYPE" == "darwin"* ]]; then
    # For macOS using Homebrew
    brew install sfml
else
    echo "Unsupported operating system. Please install SFML manually."
    exit 1
fi

echo "SFML installation completed."

echo "Setting up environment variables..."

# Set SFML_PATH environment variable
echo "export SFML_PATH=$SFML_INSTALL_PATH" >> ~/.bashrc
source ~/.bashrc

echo "Environment variables configured."

echo "Installation completed."
