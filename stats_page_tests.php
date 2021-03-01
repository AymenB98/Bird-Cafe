<?php
use PHPUnit\Framework\TestCase;
// Mock test to make sure the number of birds is positive
class statsPageTest extends TestCase
{
	public function testCountIsPositive()
	{
		$crow = new VisitStats();
		$count = $crow->birdCount(0);
		$this->assertGreaterThanOrEqual(0, $count);
	}

}

?>
