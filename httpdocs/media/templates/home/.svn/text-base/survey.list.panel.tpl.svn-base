<h2 tal:content="data/heading" />
<ul id="listComponent">
	<tal:block repeat="survey data/surveys">
		<li class="canRename" tal:attributes="id survey/id">
			<span class="hidden">
				<input type="text" tal:attributes="value survey/title" />&nbsp;
				<img alt="save" src="/media/images/apply.png" class="performRename" /> 
				<img alt="cancel" src="/media/images/cancel.png" class="performCancel" /> 
				
			</span>
			<a href="#" class="activateRenameForm" tal:content="survey/title" />
		</li>
	</tal:block>
</ul>
<div id="listComponentTools" />
