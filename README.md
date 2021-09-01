# everything

## SSH Key for github 

    ssh-keygen -t ed25519 -C "your_email@example.com"

    # start the ssh-agent in the background
    eval "$(ssh-agent -s)"

    # Add your SSH private key to the ssh-agent.
    ssh-add ~/.ssh/id_ed25519

Then add the key to github.com in settings > ssh keys

Then clone stuff like this

git clone git@github.com/username:repo

