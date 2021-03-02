<?php
use PHPUnit\Framework\TestCase;
// Test to make sure the number of birds is positive
class statsPageTest extends TestCase
{
	public function testCountIsPositive()
	{
		$crow = new VisitStats();
		$count = $crow->birdCount(0);
		$this->assertGreaterThanOrEqual(0, $count);
	}
	
	Public function testCsvCreate()
	{
		$csvTest = new CsvCreate(7, 2);
		$this->assertFileExists("visits.csv");
	}

}

?>
