#!/bin/bash

# Generating the SSH key
echo "Generating an SSH key..."
ssh-keygen -t ed25519 -N '' -f ~/.ssh/id_ed25519 -C "optional_comment"

# Starting the SSH agent
echo "Starting the SSH agent..."
eval "$(ssh-agent -s)"

# Adding the SSH key to the agent
echo "Adding the SSH key to the agent..."
ssh-add ~/.ssh/id_ed25519

# Copying the SSH key to clipboard (macOS version, adjust if on Linux)
echo "Copying the SSH key to the clipboard..."
pbcopy < ~/.ssh/id_ed25519.pub

echo "SSH key generated and copied to clipboard. Please add it to your GitHub account."
