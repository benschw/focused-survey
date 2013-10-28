<?php
/*  Mysql singleton class - used by db class in model
 *  Hangs on to one connection for multiple module instances
 *  allows for db switching
 */
class Mysql {
	
	protected static $instance;
	
	private $connection;
	public $queries = array();

//===== Setup Methods ========================================================

	public function __construct() {
		if (Config::$settings['database']['enabled']) {
			$this->connection = mysqli_connect(
				Config::$settings['database']['server'], 
				Config::$settings['database']['login'], 
				Config::$settings['database']['password'] 
			);
			$this->selectDatabase(Config::$settings['database']['database']);
		}
	}
	
	public static function singleton() {
		if (!isset(self::$instance)) {
			$className = __CLASS__;
			self::$instance = new $className;
		}
		return self::$instance;
	}

	public function __clone() {
		throw( new Exception( "cannot clone object, it is singleton" ) );
	}

	public function selectDatabase($dbName) {
		mysqli_select_db($this->connection, $dbName);
	}

	function query($sql, $connection) {
		return mysqli_query($connection, $sql);
	}

//===== Select Methods =======================================================

	public function selectResource($sql, $msg = false) {
		$this->queries[] = $sql;

		$resultResource = $this->query($sql, $this->connection);

		if ($resultResource) {
			return new MysqlIterator($resultResource);
		} else {
			throw new Exception(mysqli_error($this->connection) . "\n\n". $sql);
		}
	}

	public function selectIterator($sql, $msg = false) {
		$this->queries[] = $sql;

		$resultResource = $this->query($sql, $this->connection);

		if( $resultResource ) {
			return new MysqlIterator($resultResource);
		} else {
			throw new Exception(mysqli_error($this->connection) . "\n\n". $sql);
		}
	}

	public function select( $sql, $msg = false ) {
		$this->queries[] = $sql;

		$resultResource = $this->query($sql, $this->connection);

		if( $resultResource ) {
			if (mysqli_num_rows($resultResource) > 0) {
				while ($result = mysqli_fetch_assoc($resultResource)) {
					$results[] = $result;
				}
				return (array)$results;
			} else {
				return array();
			}
		} else {
			throw new Exception(mysqli_error($this->connection) . "\n\n". $sql);
		}
	}
	
	public function selectField( $sql, $msg = false ) {
		$this->queries[] = $sql;

		$resultResource = $this->query( $sql, $this->connection );
		
		if( $resultResource ) {
			list( $result ) = mysqli_fetch_row( $resultResource );  
			return $result;
		} else {
			throw new Exception(mysqli_error($this->connection) . "\n\n". $sql);
		}
	}

	public function count( $sql, $msg = false ) {
		$this->queries[] = $sql;

		return $this->selectField( $sql );
	}
	
	public function selectRecord( $sql, $msg = false ) {
		$this->queries[] = $sql;

		$results = $this->select( $sql );
		
		foreach( $results AS $result ) {
		  return $result;
		}
	}

	public function selectColumn( $sql, $msg = false ) {
		$this->queries[] = $sql;

		$resultResource = $this->query( $sql, $this->connection );
		
		if( $resultResource ) {
			$results = array();
			while( list( $result ) = mysqli_fetch_row( $resultResource ) ) {
				$results[] = $result;
			}
			return (array)$results;
		} else {
			throw new Exception(mysqli_error($this->connection) . "\n\n". $sql);
		}

	}
	
//===== Modify Methods =======================================================

	public function update( $sql, $msg = false ) {
		$this->queries[] = $sql;
		$resultResource = $this->query( $sql, $this->connection );

		if( $resultResource !== false ) {
			return mysqli_affected_rows( $this->connection );
		} else {
			throw new Exception(mysqli_error($this->connection) . "\n\n". $sql);
		}
	}
	
	public function insert( $sql, $msg = false ) {
		$this->queries[] = $sql;
		$resultResource = $this->query( $sql, $this->connection );

		if( $resultResource !== false ) {
			return mysqli_insert_id( $this->connection );
		} else {
			throw new Exception(mysqli_error($this->connection) . "\n\n". $sql);
		}
	}
	
	public function delete( $sql, $msg = false ) {
		$this->queries[] = $sql;
		$resultResource = $this->query( $sql, $this->connection );

		if( $resultResource !== false ) {
			return mysqli_affected_rows( $this->connection );
		} else {
			throw new Exception(mysqli_error($this->connection) . "\n\n". $sql);
		}
	}

	public static function escapeString( $msg ) {
		return mysqli_real_escape_string( $msg );
	}

}
