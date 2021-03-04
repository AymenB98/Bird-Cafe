<?php declare(strict_types=1);
use PHPUnit\Framework\TestCase;
// Test to make sure the number of birds is positive

/**
 * @covers \VisitStats
 * @covers \CsvCreate
 */
class statsPageTest extends TestCase
{
	
	/**
	 * @covers \VisitStats::birdCount
	 */
	public function testCountIsPositive()
	{
		$crow = new VisitStats();
		$count = $crow->birdCount(0);
		$this->assertGreaterThanOrEqual(0, $count);
	}
	
	/**
	 * @coversNothing
	 */
	public function testCsvCreate()
	{
		// Delete file before creating it again.
		// This means that the file does not exist
		// before the test is created.
		$csvTest = new CsvCreate(7, 2);
		$this->assertFileExists("visitNumber.csv");
	}
	
	/**
	 * @covers \CsvCreate::pythonScript
	 */
	public function testPythonExec()
	{
		$pythonTest = new CsvCreate(7, 2);
		$execValue = $pythonTest->pythonScript();
		$this->assertEquals($execValue, "Python script running");
	}

}
?>
