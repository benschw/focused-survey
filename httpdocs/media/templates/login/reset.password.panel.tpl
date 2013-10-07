<fieldset>
	<div class="content">
		<h2>Reset Password</h2>

		<p>Please enter your email, and a temporary password will be emailed to you.</p>

		<label for="loginEmail">Full Email</label>
		<input class="float" type="text" id="loginEmail" name="email" tal:attributes="value data/login" />
		<div class="clear"></div>

		<input type="submit" id="resetButton" name="reset" value="Reset" class="button" />
	</div>
	<ul id="miniNav">
		<li><a href="#" id="backToLogin">back to login</a></li>
	</ul>
</fieldset>