{include file='./header.tpl'}

<ul>
    <li>{$post["title"]}</li>
    <li>{$post["content"]|nl2br}</li>
    <li>{$post["created_at"]}</li>
</ul>

{include file='./footer.tpl'}
