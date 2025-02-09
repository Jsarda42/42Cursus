<?php
define( 'DB_NAME', 'mydatabase' );
define( 'DB_USER', 'myuser' );
define( 'DB_PASSWORD', 'mypassword' );
define( 'DB_HOST', 'mariadb:3306' );
define( 'DB_CHARSET', 'utf8mb4' );
define( 'DB_COLLATE', '' );
define( 'AUTH_KEY',         ',iPuNG8,Gqk@5DUe=%(%_M())p[:HN|QO>jY)LuL%)<d49p|AIcJimwY5$<^ 9:F' );
define( 'SECURE_AUTH_KEY',  '}vN6H__j1z=k~JKR|*dDT5OB{=d)lRd@E#qN#$!_/]XZtS2N:QI4mw=OnnCd-FX-' );
define( 'LOGGED_IN_KEY',    '7Z1#X0E[qwx+oI&cqJg6^bxCJZ?@Th~:#Yt%^c)YY_1H!qBt,i`/p4]9gW#n_Gz7' );
define( 'NONCE_KEY',        'F>do*q3e0/,bH%R6N3)Xv:L)mYcAL73K)`,<]8X5ABmt>P{jG^_unn=PsiIH^WQz' );
define( 'AUTH_SALT',        'F]LX}%.2]7Ym{PdWi.TP/O0-bE&CEcL.C>!;=V[]v)s;J=$5q3v4oaPDy?ZH?*Ur' );
define( 'SECURE_AUTH_SALT', 'Zbr# v&0&n}%r|-Yd/HmHSp&F.m$[@$n5%@j?fSo8Y-AfLrI #r8ZK7 I&XL*F#H' );
define( 'LOGGED_IN_SALT',   '!.{_X +2 /$7TMkI8BGt!8k8Zy&gs~n{-[kYqo+lztqdLy8nHQkO:^OKO{h@N+B.' );
define( 'NONCE_SALT',       '(;~#79xm6qOM0RhEaQhDBha.xJXj B0IR#NHn{=RA@dW(]]9rDl`@WnVnA=gfQDQ' );
$table_prefix = 'wp_';
define( 'WP_DEBUG', false );
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}
require_once ABSPATH . 'wp-settings.php';
