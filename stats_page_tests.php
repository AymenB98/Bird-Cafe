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
	
	public function testCsvCreate()
	{
		$csvTest = new CsvCreate(7, 2);
		$this->assertFileExists("visits.csv");
	}
	
	public function testPythonExec()
	{
		$pythonTest = new csVCreate(3, 1);
		$execValue = $pythonTest->pythonScript();
		$this->assertEquals($execValue, "Python script running");
		
	}
	
}

?>
