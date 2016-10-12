#################################################
##	CloudBrew - Software Defined Distributed Public Cloud Storage
##	Install the required LTS node version with nvm

##	Author: 	Runcy Oommen
##	Date:	08/03/2016

##	Copyright 2016 CloudBrew Systems. All rights reserved.
#################################################

## Pls update to node versions to the next available LTS as required after sufficient tests. Update the comments below as well with date/version ##

## 27-Jul-2016 - Node LTS ver 4.4.7 is being used as starters ##
## 17-Sep-2016 - Node updated to LTS ver 4.5.0 ##

#!/usr/bin/bash
NODE_VERSION="4.5.0"

. ~/.nvm/nvm.sh

nvm install $NODE_VERSION

## Install node-gyp ##
npm install -g node-gyp

## Source bashrc ##
source ~/.bashrc

