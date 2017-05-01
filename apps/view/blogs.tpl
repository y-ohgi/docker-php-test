{include file='./header.tpl'}

<ul>
    {foreach $blogs as $blog}
	<li>
	    <a href="/blogs.php?id={$blog["id"]}">
		{$blog["title"]}
	    </a>
	</li>
    {/foreach}
</ul>

{include file='./footer.tpl'}
