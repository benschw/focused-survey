var LoginManager = new Class({

	Implements: [Options],  
	options: {},  
  
	initialize: function(options) {  
    this.setOptions(options);  
		this.loadLoginForm();
	},	
	
	loadLoginForm : function() {
		var request = new Request.HTML({
			url: 'fw.Account.Public.getLogin', 
			update: $('login'),
			onSuccess : function() {
				this.setupMenu();
				if( $('loginButton') ) {
					$('loginButton').addEvent( 'click', function(event) {
						this.login();
					}.bind(this));
				}
			}.bind(this)
		}).get();
	},
	loadResetPasswordForm : function() {
		var request = new Request.HTML({
			url: 'fw.Account.Public.getResetPassword', 
			update: $('login'),
			onSuccess : function() {
				this.setupMenu();
				if( $('resetButton') ) {
					$('resetButton').addEvent( 'click', function(event) {
						this.resetPassword();
					}.bind(this));
				}
			}.bind(this)
		}).get({ login : $('loginEmail').value });
	
	},
	loadNewAccountForm : function() {
		var request = new Request.HTML({
			url: 'fw.Account.Public.getNewAccount', 
			update: $('login'),
			onSuccess : function() {
				this.setupMenu();
				if( $('createButton') ) {
					$('createButton').addEvent( 'click', function(event) {
						this.createAccount();
					}.bind(this));
				}
			}.bind(this)
		}).get();
	},
	loadPasswordChangeForm : function() {
		var request = new Request.HTML({
			url: 'fw.Account.Public.getForcePasswordChange', 
			update: $('login'),
			onSuccess : function() {
				this.setupMenu();
				if( $('performReset') ) {
					$('performReset').addEvent( 'click', function(e) {
						this.changePassword();
					}.bind(this));
				}
			}.bind(this)
		}).get();
	},
	//==========================================================================
	// Actions
	//==========================================================================
	login : function() {
		var request = new Request.JSON({
			url: 'fw.Account.Public.login', 
			data : { email : $('loginEmail').value, password : $('password').value },
			onSuccess : function( response ) {
				if( response.result == true ) {
					if( response.isTemporary ) {
						this.loadPasswordChangeForm();
					} else {
						window.location = '/home';
					}
				} else {
					$('loginEmail').addClass( 'error' );
					$('password').addClass( 'error' );
					alert( "Username and password do not match." );
				}
			}.bind(this)
		}).send();
	},
	createAccount : function() {
		var request = new Request.JSON({
			url: 'fw.Account.Public.addAccount', 
			data : { email : $('loginEmail').value, password : $('password').value, password2 : $('password2').value },
			onSuccess : function( response ) {
				if( response.result == true ) {
					var request = new Request.HTML({
						url: 'fw.Account.Public.getAddCreateSuccess', 
						update: $('login'),
						onSuccess : function() {
							this.setupMenu();
						}.bind(this)
					}).get();
				} else {
					$('loginEmail').addClass( 'error' );
					$('password').addClass( 'error' );
					$('password2').addClass( 'error' );
					alert( response.message );
				}
			}.bind(this)
		}).send();
	},
	changePassword : function() {
		var request = new Request.JSON({
			url: 'fw.Account.Authenticated.changePassword', 
			data : { password : $('password').value, password2 : $('password2').value },
			onSuccess : function( response ) {
				if( response.result ) {
					window.location = '/home';
				} else {
					alert( response.message );
				}
			}.bind(this)
		}).send();
	},
	resetPassword : function() {
		var request = new Request.JSON({
			url: 'fw.Account.Public.resetPassword', 
			data : { email : $('loginEmail').value },
			onSuccess : function( response ) {
				if( response.result == true ) {
					var request = new Request.HTML({
						url: 'fw.Account.Public.getResetResponse', 
						update: $('login'),
						onSuccess : function() {
							this.setupMenu();
						}.bind(this)
					}).get();
				} else {
					alert( "Sorry. We do not have a record of that email address" );
				}
			}.bind(this)
		}).send();
	},

	//==========================================================================
	// Helper
	//==========================================================================
	setupMenu : function() {
		if( $('resetPassword') ) {
			$('resetPassword').addEvent( 'click', function(event) {
				this.loadResetPasswordForm();
			}.bind(this));
		}
		if( $('newAccount') ) {
			$('newAccount').addEvent( 'click', function(event) {
				this.loadNewAccountForm();
			}.bind(this));
		}
		if( $('backToLogin') ) {
			$('backToLogin').addEvent( 'click', function(event) {
				this.loadLoginForm();
			}.bind(this));
		}		
	}
});