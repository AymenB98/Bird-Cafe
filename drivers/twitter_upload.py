# MIT License
# Copyright (c) 2009-2021 Joshua Roesslein

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.

# Author: Aymen Benylles
# This code has been adapted from the "oauth.py" example from the "examples" 
# folder in the GitHub repo for the tweepy Twitter API Python library. 
# This can be found in the following link:
# https://github.com/tweepy/tweepy/blob/master/examples/oauth.py.
# This is a building block for future code for this project.
# This was also based on code for image compression which can be found
# via the following links: https://sempioneer.com/python-for-seo/how-to-compress-images-in-python/
# https://www.geeksforgeeks.org/how-to-compress-images-using-python-and-pil/ 

import tweepy
from PIL import Image

## A class which uploads a simple Tweet
#  This class also has a method which allows the user to check
#  which account they are using.
class SimpleTweet:

    ## The constructor for this class automaically uploads a
    #  Tweet when the class has been instantiated
    #  @param tweetString Characters that will be uploaded
    #
    def __init__(self, tweetString):
        ## @var tweet The Tweet to be uploaded
        self.tweet = tweetString
        # Variables for oauth
        # These can be found on the Twitter Developer account
        keys = open("../../drivers/keys.txt", "r")

        # Read API keys from .txt file and assign them to appropriate variables
        apiKeys = keys.read().splitlines()

        self.accessToken = apiKeys[0]
        self.accessTokenSecret = apiKeys[1]
        self.consumerKey = apiKeys[2]
        self.consumerSecret = apiKeys[3]

        keys.close()

        auth = tweepy.OAuthHandler(self.consumerKey, self.consumerSecret)
        auth.set_access_token(self.accessToken, self.accessTokenSecret)
        self.twitterApi = tweepy.API(auth)

    ## Upload compressed image with string
    #  
    #
    def makeTweet(self):
        self.twitterApi.update_with_media("../../Photos/compressed_birdcafe.jpg", status=self.tweet)
    ## Lightly compress image to allow Twitter uplaod
    #  
    #
    def compressImage(self):
        # Open original image of bird
        picture = Image.open("../../Photos/birdcafe.jpg")
        # Compress image for Twitter upload
        picture.save("../../Photos/compressed_birdcafe.jpg", optimize=True, quality=99)


    ## Display name of Twitter account in use
    #  
    #
    def printAccount(self):
        print(self.twitterApi.me().name)
        return self.twitterApi.me().name

# String to be uploaded to Twitter with image
tweet = "Bird detected"

# Make Tweet
trialTweet = SimpleTweet(tweet)
trialTweet.compressImage()
trialTweet.makeTweet()