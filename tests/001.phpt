--TEST--
Check for intl_dtpg presence
--SKIPIF--
<?php if (!extension_loaded("intl_dtpg")) print "skip"; ?>
--FILE--
<?php
$dtpg = new IntlDateTimePatternGenerator('ru_RU');
$ruPattern = $dtpg->findBestPattern('MMMMd');
$dtpg = new IntlDateTimePatternGenerator('en_US');
$enPattern = $dtpg->findBestPattern('MMMMd');
echo $ruPattern . ';' . $enPattern;
?>
--EXPECT--
d MMMM;MMMM d
