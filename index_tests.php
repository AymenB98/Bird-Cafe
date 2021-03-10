<?php declare(strict_types=1);
use PHPUnit\Framework\TestCase;

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
		$this->assertEquals(0, !$newSocket);
	}
	
}
?>
