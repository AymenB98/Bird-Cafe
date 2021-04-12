# coding=utf-8

# Author: Aymen Benylles
# This code has been adapted from code found at the following link:
# https://docs.python.org/3/library/unittest.html

import unittest
from twitter_upload import SimpleTweet

class TestTweepyApi(unittest.TestCase):
    # Test that the user has actually created an object with the
    # correct Twitter account
    def testUser(self):
        tweet = "test"
        newTweet = SimpleTweet(tweet)
        user = newTweet.printAccount()
        self.assertEqual(user, u"Bird Caf\xe9")


if __name__ == '__main__':
    unittest.main()

