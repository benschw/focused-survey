var MBox = new Class({
	handle : null,
	url : null,
	
	wrapper : null,
	innerWrapper : null,
	
	Implements: [Options, Events],
	options: {
		url    : null,
		width  : 300,
		height : 300,
		title  : ''
	},
	
	initialize : function( handle, options) {
		this.setOptions(options);
		this.handle = $(handle);
		if( handle.href ) {
			this.url = handle.href;
		}
		this.handle.addEvent( 'click', function(e) {
			var ev = new Event(e).stop();
			this.open();
		}.bind(this));
	},

	open : function() {
		var w = this.options.width - 66;
		var h = this.options.height - 66;

		this.wrapper = new Element( 'div', { 
			'class'  : 'mbox_wrapper', 
			'styles' : {
				'width'  : this.options.width + "px",
				'height' : this.options.height + "px"
			}
		});
		this.innerWrapper = new Element( 'div', { 
			'class' : 'mbox_innerWrapper',
			'styles' : {
				'float'  : 'left',
				'width'  : w + "px",
				'height' : h + "px"
			}
		});

		this.wrapper.appendChild( new Element( 'div', { 'class' : 'mbox_bg-nw mbox_bg' }) );
		this.wrapper.appendChild( new Element( 'div', { 
			'class' : 'mbox_bg-n mbox_bg',
			'styles' : {
				'width' : w + "px"
			}
		}) );
		this.wrapper.appendChild( new Element( 'div', { 'class' : 'mbox_bg-ne mbox_bg' }) );
		this.wrapper.appendChild( new Element( 'div', { 'class' : 'mbox_clear' }) );
		this.wrapper.appendChild( new Element( 'div', { 'class' : 'mbox_bg-w mbox_bg', 'styles' : {
			'height' : h + "px"
		}  }) );
		this.wrapper.appendChild( this.innerWrapper );
		this.wrapper.appendChild( new Element( 'div', { 'class' : 'mbox_bg-e mbox_bg', 'styles' : {
			'height' : h + "px"
		}  }) );
		this.wrapper.appendChild( new Element( 'div', { 'class' : 'mbox_clear' }) );
		this.wrapper.appendChild( new Element( 'div', { 'class' : 'mbox_bg-sw mbox_bg' }) );
		this.wrapper.appendChild( new Element( 'div', { 
			'class' : 'mbox_bg-s mbox_bg',
			'styles' : {
				'width' : w + "px"
			}
		}) );
		this.wrapper.appendChild( new Element( 'div', { 'class' : 'mbox_bg-se mbox_bg' }) );
		var header = new Element( 'h2' );
		var image = new Element( 'img', {
			'src'    : '/media/images/remove-big.png',
			'alt'    : 'Close',
			'styles' : {
				'cursor' : 'pointer',
				'float'  : 'right'
			}
		})
		var span = new Element('span');
		span.innerHTML = this.options.title;
		
		header.appendChild( image );
		header.appendChild( span );
		this.innerWrapper.appendChild( header );

		var url = this.url;
		if( this.options.url ) {
			url = this.options.url;
		}
		var request = new Request.HTML({
			url: url, 
			onSuccess : function( tree, elems, html, js ) {
				var height = window.getSize().y;
				
				this.innerWrapper.innerHTML += html;
				$$('body')[0].appendChild( this.wrapper );
				var h = window.getSize().y;
				var w = window.getSize().x;
				var top  = ( h - this.options.height ) / 2;
				var left = ( w - this.options.width ) / 2;
				
				this.wrapper.getElement('img').addEvent( 'click', function(e) {
					this.close();
				}.bind(this));
				

				this.wrapper.setStyle( 'top',  top + "px" );
				this.wrapper.setStyle( 'left', left + "px" );
				
				this.wrapper.addEvent( "click", function(e) {
					new Event(e).stop();
				});
				window.addEvent( "click", function(e) {
					this.close();
				}.bind(this));
				
			}.bind(this)
		}).get();
	},
	
	close : function() {
		this.wrapper.destroy();
	}
	
});