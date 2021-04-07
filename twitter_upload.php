<?php
// The MIT License (MIT)

// Copyright (c) 2013 James Mallison (j7mbo.co.uk)

// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

// This was also based on code from https://www.madebymagnitude.com/blog/how-to-automatically-send-tweets-in-php/

// This code has been adapted from these sources by Aymen Benylles

require_once('TwitterAPIExchange.php');

class MakeTweet 
{
    /* @brief	Constructor which sets up API keys and instanciates class
	 * 
	 * @return none 
	 */
    function __construct()
    {
        // Get API keys from .env file
        $keys = file(".env", FILE_IGNORE_NEW_LINES | FILE_SKIP_EMPTY_LINES);

        // Create array full of API keys
        $apiKeys = array(
            "oauth_access_token" => $keys[0],
            "oauth_access_token_secret" => $keys[1],
            "consumer_key" => $keys[2],
            "consumer_secret" => $keys[3]
        );

        $this->apiKeys = $apiKeys;
        // Create new Twitter object
        $twitter = new TwitterAPIExchange($apiKeys);
        $this->twitter = $twitter;
    }

    /* @brief	Perform request to get media ID of image to be sent
	 * 
	 * @return none 
	 */
    function getMediaId()
    {
        // Create new Twitter object
        $twitter = new TwitterAPIExchange($this->apiKeys);

        // Get file contents of picture to Tweet
        $picture = file_get_contents("bird_logo_pink.jpg");
        // Encode this data into correct format
        $pictureData = base64_encode($picture);

        // First, get media ID from Twitter, then use that to upload image
        $url = "https://upload.twitter.com/1.1/media/upload.json";
        $requestMethod = "POST";
        $setField = array("media_data" => $pictureData);

        // Make request
        $pictureData = $this->twitter->setPostfields($setField)
                            ->buildOauth($url, $requestMethod)
                            ->performRequest();

        // Decode image data so it can be uploaded
        $pictureData = @json_decode($pictureData, TRUE);
        // Needs to be media_string_id, not media_string
        $mediaID = $pictureData["media_id_string"];
        $this->mediaID = $mediaID;
    }

    /* @brief   Use media ID to upload image to Twitter
	 * 
	 * @return none 
	 */
    function uploadImage()
    {
        // Now that media_id for image has been obtained, upload image
        $url = "https://api.twitter.com/1.1/statuses/update.json";
        $requestMethod = "POST";
        $setField = array(
            "status" => "Test picture",
            "possibly_sensitive" => FALSE,
            "media_ids" => $this->mediaID);
        // Make request for upload
        $this->twitter->setPostfields($setField)
                ->buildOauth($url, $requestMethod)
                ->performRequest();
    }

};

// Start timer 
$startTime = hrtime(true);

// Make Tweet
$newTweet = new MakeTweet();
$newTweet->getMediaId();
$newTweet->uploadImage();

// Stop timer
$endTime = hrtime(true);
$execTime = $endTime - $startTime;
$execTimeMs = $execTime / 1000000;
echo "<b> Execution time: " .$execTimeMs. " ms </b>"; 
?>