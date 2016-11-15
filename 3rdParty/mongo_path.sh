#################################################
##	CloudBrew - Software Defined Distributed Public Cloud Storage
##	Create symbolic link for mongo to /usr/bin for easy invokation

##	Author:	Runcy Oommen
##	Date:	09/20/2016

##	Copyright 2016 CloudBrew Labs LLP. All rights reserved.
#################################################

#!/usr/bin/bash
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/bsondump /usr/bin/bsondump
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongo /usr/bin/mongo
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongod /usr/bin/mongod
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongodump /usr/bin/mongodump
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongoexport /usr/bin/mongoexport
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongofiles /usr/bin/mongofiles
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongoimport /usr/bin/mongoimport
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongooplog /usr/bin/mongooplog
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongoperf /usr/bin/mongoperf
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongorestore /usr/bin/mongorestore
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongos /usr/bin/mongos
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongostat /usr/bin/mongostat
sudo ln -sf /usr/local/cloudbrew/mongodb/bin/mongotop /usr/bin/mongotop

