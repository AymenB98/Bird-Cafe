<?php declare(strict_types=1);
use PHPUnit\Framework\TestCase;

/**
 * @covers \VisitStats
 * @covers \CsvCreate
 */
class StatsPageTest extends TestCase
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
		$this->assertFileExists("official.csv");
	}
	
	/**
	 * @coversNothing
	 */
	public function testEmptyLine()
	{
		// Make sure that an empty line has not been written
		// at the top of the csv file.
		$emptyTest = new CsvCreate(7,2);
		
		$csvHandle = fopen("official.csv", "a+");
		$firstLine = fgetcsv($csvHandle, 1000, ",");
		fclose($csvHandle);
		
		$this->assertNotFalse($firstLine[0][0]);
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
