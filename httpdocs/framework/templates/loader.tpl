<metal:block define-macro="loader">

	<tal:block tal:condition="exists: data/inlineJS">
		<script type="text/javascript" tal:content="structure data/inlineJS | null"></script>
	</tal:block>

	<metal:block use-macro="${templatePath}${data/template}/${data/panelStyle}" />

</metal:block>

