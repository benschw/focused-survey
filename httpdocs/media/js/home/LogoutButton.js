var LogoutButton = Class({
	
	initialize : function( id ) {
		$(id).addEvent( 'click', function() {
			this.logout();
		}.bind(this));
	},
	
	logout : function() {
		var request = new Request.JSON({
			url: 'fw.Account.Authenticated.logout', 
			onSuccess: function( response ) {				
				window.location = "/";
			}
		}).send();
	}
});
