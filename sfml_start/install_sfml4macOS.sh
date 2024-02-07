#!/bin/bash

SFML_VERSION="2.6.1"
SFML_INSTALL_PATH="/usr/local"

echo "Installing SFML..."

# Install SFML using Homebrew
brew install sfml

echo "SFML installation completed."

echo "Setting up environment variables..."

# Set SFML_PATH environment variable
echo "export SFML_PATH=$SFML_INSTALL_PATH" >> ~/.bash_profile
source ~/.bash_profile

echo "Environment variables configured."

echo "Installation completed."