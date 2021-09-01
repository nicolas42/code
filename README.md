# everything

## SSH Key for github 

    ssh-keygen -t ed25519 -C "your_email@example.com"

    # start the ssh-agent in the background
    eval "$(ssh-agent -s)"

    # Add your SSH private key to the ssh-agent. If you created your key with a different name, or if you are adding an existing key that has a different name, replace id_ed25519 in the command with the name of your private key file.
    ssh-add ~/.ssh/id_ed25519
