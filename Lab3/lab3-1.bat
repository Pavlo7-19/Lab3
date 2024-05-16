chcp 65001
mkdir ПЗ-23-2\Водоп'янов.П.Д.\batch\СкрытаяПапка ПЗ-23-2\Водоп'янов.П.Д.\batch\НеСкрытаяПапка
attrib +h ПЗ-23-2\Водоп'янов.П.Д.\batch\СкрытаяПапка
xcopy /? > ПЗ-23-2\Водоп'янов.П.Д.\batch\НеСкрытаяПапка\copyhelp.txt
xcopy /f /a ПЗ-23-2\Водоп'янов.П.Д.\batch\НеСкрытаяПапка\copyhelp.txt ПЗ-23-2\Водоп'янов.П.Д.\batch\СкрытаяПапка\copyhelp.txt
ren "ПЗ-23-2\Водоп'янов.П.Д.\batch\СкрытаяПапка\copyhelp.txt" copied_copyhelp.txt
pause >nul
