<metal:block define-macro="component">
  <tal:block tal:attributes="id data/panelID | null; class data/panelClass | null">
    <metal:block use-macro="panelCommon" />
  </tal:block>
</metal:block>

<metal:block define-macro="div">
  <div tal:attributes="id data/panelID | null; class data/panelClass | null">
    <metal:block use-macro="panelCommon" />
  </div>
</metal:block>





<metal:block define-macro="panelCommon">
  <tal:block repeat="component data/components">
    <metal:block tal:define="data component" use-macro="${templatePath}loader.tpl/loader" />
  </tal:block>
</metal:block>

