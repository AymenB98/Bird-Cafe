<?php declare(strict_types=1);
use PHPUnit\Framework\TestCase;
// Author: Aymen Benylles
// This code was based on example code which can be found on 
// https://phpunit.readthedocs.io/en/9.0/writing-tests-for-phpunit.html
// This website also provides instructions on how to perform coverage
// analysis with PHPUnit


/**
 * @covers \UdpSocket
 */
class IndexPageTest extends TestCase
{
	
	/**
	 * @covers \UdpSocket::__construct  
	 */
	public function testUdpSocket()
	{
		$newSocket = new UdpSocket();
		$this->assertNotFalse($newSocket);
	}

	/**
	 * @covers \UdpSocket::csvContents
	 */
	public function testCsvCreate()
	{
		// Delete file before creating it again.
		// This means that the file does not exist
		// before the test is created.
		$csvTest = new UdpSocket();
		$this->assertFileExists("official.csv");
	}
	
	/**
	 * @covers \UdpSocket::csvAppend
	 */
	public function testTime()
	{
		// Make sure time recorded is not negative
		$emptyTest = new UdpSocket();
		$lastTime = $emptyTest->csvAppend(0); 
		
		$this->assertGreaterThanOrEqual(0, $lastTime);
	}


	/**
	 * @covers \UdpSocket::lastUpdateTime
	 */
	public function testTimeDays()
	{
		// Make sure time recorded is not negative
		$timeTest = new UdpSocket();
		// Input a time equal to more than two days in the past
		// 86400s in a day, 86400000ms in a day
		$twoDaysAgo = (time()*1000) - (2*86400000); 
		$timeDiff = $timeTest->lastUpdateTime($twoDaysAgo);

		$this->assertGreaterThanOrEqual($timeDiff, $twoDaysAgo);
	}

	/**
	 * @covers \UdpSocket::lastUpdateTime
	 */
	public function testTimeDiffHours()
	{
		// Make sure time recorded is not negative
		$timeTest = new UdpSocket();
		// Input a time equal to more than two days in the past
		// 3600s in an hour, 3600000ms in an hour
		$twoHoursAgo = (time()*1000) - (2*3600000); 
		$timeDiff = $timeTest->lastUpdateTime($twoHoursAgo);

		$this->assertGreaterThanOrEqual($timeDiff, $twoHoursAgo);
	}

	/**
	 * @covers \UdpSocket::lastUpdateTime
	 */
	public function testTimeDiffMinutes()
	{
		// Make sure time recorded is not negative
		$timeTest = new UdpSocket();
		// Input a time equal to more than two days in the past
		// 60s in  minute, 60000ms in a minute
		$twoMinsAgo = (time()*1000) - (2*60000); 
		$timeDiff = $timeTest->lastUpdateTime($twoMinsAgo);

		$this->assertGreaterThanOrEqual($timeDiff, $twoMinsAgo);
	}

}
?>
