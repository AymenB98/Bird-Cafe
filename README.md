# Bird-Cafe
This is the software for an autonomous bird feeder which will do the following: 
- release food when a bird lands on it.
- take a picture of the bird and upload it to a server on a Raspberri Pi. 
- use machine learning to make sure it was a bird that landed on the feeder, and not something else.
- Tweet an image of the bird with a caption.

A GUI front end will also be created to allow a user to interact with the system easily.

This project is being completed for Real Time Embedded Programming 5 at the University of Glasgow by Aymen Benylles, Joe Costello, Alena Larionova and Jonathan Roarty.
## Social Media
![Tweet](https://img.shields.io/twitter/url?style=social&url=https%3A%2F%2Ftwitter.com%2Fsmartbirdcafe)
![Follow](https://img.shields.io/twitter/follow/smartbirdcafe?style=social&logo=twitter)
![Watchers](https://img.shields.io/github/watchers/AymenB98/Bird-Cafe?style=social)
## Technologies
![NGINX](https://img.shields.io/badge/server-nginx-blue) ![PHP](https://img.shields.io/badge/PHP-v7.3.27-orange) ![python](https://img.shields.io/badge/python-v2.7.16-brightgreen)
![PHPUNIT](https://img.shields.io/badge/PHPUnit-v7.5.6-orange)
## Web Server
An NGINX server was setup on the Pi to host a webpage displaying stats about the bird feeder. Instructions on how to setup an NGINX server on a Raspberry Pi can be found via the following link: https://www.raspberrypi.org/documentation/remote-access/web-server/nginx.md.

The bulk of the code enabling the web server is written in PHP. There are several unit tests in this repo that can be found in the php_tests.php file. To run these tests, open a terminal and do the following:
- Navigate to the directory of your index.php and stats_page.php files:
```
/var/www/html
```
- Enter the following command:
```
phpunit --bootstrap stats_page.php stats_page_tests.php
```
Once these steps have been completed, the tests should have been performed successfully.
