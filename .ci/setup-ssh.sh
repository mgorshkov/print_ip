#!/bin/bash
# setup-ssh.sh: load the SSH key 

set -ev
declare -r SSH_FILE="$(mktemp -u $HOME/.ssh/travis_temp_ssh_key_XXXX)"
# Decrypt the file containing the private key
openssl aes-256-cbc \
  -K $encrypted_e848c9b7a16f_key \
  -iv $encrypted_e848c9b7a16f_iv \
  -in ".ci/travis_deploy_key.enc" \
  -out "$SSH_FILE" -d
# Enable SSH authentication
chmod 600 "$SSH_FILE" \
  && printf "%s\n" \
       "Host github.com" \
       "  IdentityFile $SSH_FILE" \
       "  LogLevel ERROR" >> ~/.ssh/config