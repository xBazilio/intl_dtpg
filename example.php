<?php

foreach (['ru_RU', 'en_US', 'fr_FR', 'zh_CN', 'fa_IR'] as $locale) {
    echo $locale, PHP_EOL;

    $dtpg = new IntlDateTimePatternGenerator($locale);

    foreach (['MMMMd', 'MMMdHHmm', 'YYMMM', 'eeeeMMMMdH'] as $skeleton) {
        $pattern = $dtpg->findBestPattern($skeleton);
        $formatted = (new IntlDateFormatter($locale, 0, 0, null, null, $pattern))->format(1455111783);
        printf("  %s: %s => %s\n", $skeleton, $pattern, $formatted);
    }
}
