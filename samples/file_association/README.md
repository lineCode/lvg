Linux .lvg and .swf file association
==========

Put lvg player executable in ~/bin, change "[user]" in lvg.desktop to your system user name.
Put lvg.desktop mimeapps.list to ~/.local/share/applications and lvg.xml to ~/.local/share/mime/packages .
Run commands:
update-desktop-database ~/.local/share/applications
update-mime-database    ~/.local/share/mime
