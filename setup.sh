#!/bin/bash

## FIGLET ##
wget https://raw.githubusercontent.com/xero/figlet-fonts/master/Basic.flf

# move to default directory
sudo mv Basic.flf "$(figlet -I 2)/"
