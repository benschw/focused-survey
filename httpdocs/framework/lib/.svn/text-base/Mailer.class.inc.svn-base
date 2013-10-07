<?php

class Mailer {
	protected $charset 	= "us-ascii";
	protected $encoding = "7bit";

	protected $to 	= array();
	protected $cc 	= array();
	protected $bcc 	= array();

	protected $fromEmail;
	protected $fromName;
	protected $replyEmail;
	protected $replyName;

	protected $subject;
	protected $body;

	public function __construct() {

	}


	public function setSubject( $subject ) {
		$this->subject = $subject;
	}
	public function setBody( $body ) {
		$this->body = $body;
	}

	public function setFrom( $address, $name = null) {
		$this->fromEmail 	= $address;
		$this->fromName 	= $name;
	}

	public function setReply( $address, $name = null) {
		$this->replyEmail = $address;
		$this->replyName 	= $name;
	}

	public function setTo( $to ) { 
		$this->to = ( is_array( $to ) ? $to : array( $to ) );
	}

	public function setCC( $cc ) {
		$this->cc = ( is_array( $cc ) ? $cc : array( $cc ) );
	}

	public function setBcc( $bcc ) {
		$this->bcc = ( is_array( $bcc ) ? $bcc : array( $bcc ) );
	}

	public function send() {
		if( !mail( implode( ", ", $this->to ), $this->subject, $this->body, $this->getHeaders() ) ) {
			throw new MailerException( "mail() failed:\n.{$this}"  );
		}
	}

	//==========================================================================

	protected function getHeaders() {
		$headers = array();
		
		if( !is_null( $this->fromEmail ) ) {
			if( !is_null( $this->fromName ) ) {
				$headers['From'] = "{$this->fromName}<{$this->fromEmail}>";
				$headers['Return-Path'] = "{$this->fromName}<{$this->fromEmail}>";
			} else {
				$headers['From'] = $this->fromEmail;
				$headers['Return-Path'] = $this->fromEmail;
			}
		}
		if( !is_null( $this->replyEmail ) ) {
			if( !is_null( $this->replyName ) ) {
				$headers["Reply-To"] = "{$this->replyName}<{$this->replyEmail}>";
			} else {
				$headers["Reply-To"] = $this->replyEmail;
			}
		} else if( !is_null( $this->fromEmail ) ) {
			$headers["Reply-To"] = $headers['From'];
		}

		if( count( $this->cc ) > 0 ) {
			$headers['CC'] = implode( ", ", $this->cc );
		}
		if( count( $this->bcc ) > 0 )  {
			$headers['BCC'] = implode( ", ", $this->bcc );
		}

		if( $this->charset != "" ) {
			$headers["Mime-Version"] = "1.0";
			$headers["Content-Type"] = "text/plain; charset={$this->charset}";
			$headers["Content-Transfer-Encoding"] = $this->encoding;
		}

		$headers["X-Mailer"] = "php " . phpversion();
	
		$headerStr = '';
		foreach( $headers AS $key => $val ) {
			$headerStr .= "{$key}: {$val}\r\n";
		}
		return $headerStr;
	}

	public function __toString() {
		return 	"To: " . implode( ', ', $this->to ) . "\n" . 
						$this->getHeaders() . "\n" . 
						$this->subject . "\n" . 
						$this->body;
	}

}


?>
