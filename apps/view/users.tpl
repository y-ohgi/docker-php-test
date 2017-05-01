{include file='./header.tpl'}

<ul>
    {foreach $users as $user}
	<li>{$user["name"]}</li>
	<li>
	    <ul>
		<li>{$user["email"]}</li>
		<li>{$user["description"]}</li>
		<li>{$user["created_at"]}</li>
	    </ul>
	</li>
    {/foreach}
</ul>

{include file='./footer.tpl'}
