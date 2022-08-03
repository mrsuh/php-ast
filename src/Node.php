<?php

namespace Mrsuh\PhpAst;

final class Node
{
    public string $kind     = "";
    public string $value    = "";
    public int    $lineno   = 0;
    /** @var Node[] */
    public array  $children = [];
}
