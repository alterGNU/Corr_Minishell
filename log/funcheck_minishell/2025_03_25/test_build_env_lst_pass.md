=[ CAS ev-->NULL ]========================================================================
build_env_lst(NULL)
✴ t_list *env={
 ⮡ {PWD=/home/altergnu/Data/shared/42/C3_minishell/Minishell/tests},
 ⮡ {SHLVL=1},
 ⮡ {_=/home/altergnu/Data/shared/42/C3_minishell/Minishell/tests./minishell},
 ⮡ NULL }
=======================================================================================> ✅
=[ CAS ev-->[NULL] ]======================================================================
build_env_lst([NULL])
✴ t_list *env={
 ⮡ {PWD=/home/altergnu/Data/shared/42/C3_minishell/Minishell/tests},
 ⮡ {SHLVL=1},
 ⮡ {_=/home/altergnu/Data/shared/42/C3_minishell/Minishell/tests./minishell},
 ⮡ NULL }
======================================================================================= ✅
=[ CAS ev-->OK but manually created ]=====================================================
build_env_lst(["arg1=toto", "arg2=titi", "arg3=titi", "arg4=titi", NULL])
✴ t_list *env={
 ⮡ {arg1=toto},
 ⮡ {arg2=titi},
 ⮡ {arg3=titi},
 ⮡ {arg4=titi},
 ⮡ NULL }
======================================================================================= ✅
=[ CAS ev-->real env ]====================================================================
build_env_lst(["SYSTEMD_EXEC_PID=3008", "SSH_AUTH_SOCK=/run/user/1000/keyring/ssh", "SESSION_MANAGER=local/altergnu-HP:@/tmp/.ICE-unix/2867,unix/altergnu-HP:/tmp/.ICE-unix/2867", "GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/3f645528_c6c0_411e_8fc3_0776b2025fa1", "LANG=en_US.UTF-8", "XDG_CURRENT_DESKTOP=ubuntu:GNOME", "PWD=/home/altergnu/Data/shared/42/C3_minishell/Minishell/tests", "QT_IM_MODULE=ibus", "GPG_AGENT_INFO=/run/user/1000/gnupg/S.gpg-agent:0:1", "DESKTOP_SESSION=ubuntu", "USER=altergnu", "XDG_MENU_PREFIX=gnome-", "HOME=/home/altergnu", "DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus", "GTK_MODULES=gail:atk-bridge", "XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg", "WINDOWPATH=2", "XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop", "XDG_SESSION_DESKTOP=ubuntu", "GSM_SKIP_SSH_AGENT_WORKAROUND=true", "GNOME_DESKTOP_SESSION_ID=this-is-deprecated", "QT_ACCESSIBILITY=1", "DEBUGINFOD_URLS=https://debuginfod.ubuntu.com ", "LOGNAME=altergnu", "GNOME_TERMINAL_SERVICE=:1.115", "PATH=/home/altergnu/.local/funcheck/host:/home/altergnu/.local/bin:/home/altergnu/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin", "MEMORY_PRESSURE_WRITE=c29tZSAyMDAwMDAgMjAwMDAwMAA=", "XMODIFIERS=@im=ibus", "SHELL=/usr/bin/zsh", "XDG_SESSION_TYPE=x11", "GNOME_SHELL_SESSION_MODE=ubuntu", "XDG_RUNTIME_DIR=/run/user/1000", "USERNAME=altergnu", "VTE_VERSION=7600", "MEMORY_PRESSURE_WATCH=/sys/fs/cgroup/user.slice/user-1000.slice/user@1000.service/session.slice/org.gnome.SettingsDaemon.MediaKeys.service/memory.pressure", "GNOME_KEYRING_CONTROL=/run/user/1000/keyring", "XAUTHORITY=/run/user/1000/gdm/Xauthority", "COLORTERM=truecolor", "DISPLAY=:1", "TERM=xterm-256color", "GDMSESSION=ubuntu", "XDG_SESSION_CLASS=user", "SHLVL=1", "OLDPWD=/home/altergnu/Data/shared/42/C3_minishell/Minishell", "ZSH=/home/altergnu/.oh-my-zsh", "VIMRC=/home/altergnu/.vim/vimrc", "CLE=/media/altergnu/Lexar/", "DOTPATH=/home/altergnu/Projects/Dotfiles", "PAGER=less", "LESS=-R", "LSCOLORS=Gxfxcxdxbxegedabagacad", "LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=00:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.avif=01;35:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:*~=00;90:*#=00;90:*.bak=00;90:*.crdownload=00;90:*.dpkg-dist=00;90:*.dpkg-new=00;90:*.dpkg-old=00;90:*.dpkg-tmp=00;90:*.old=00;90:*.orig=00;90:*.part=00;90:*.rej=00;90:*.rpmnew=00;90:*.rpmorig=00;90:*.rpmsave=00;90:*.swp=00;90:*.tmp=00;90:*.ucf-dist=00;90:*.ucf-new=00;90:*.ucf-old=00;90:", "_=/home/altergnu/.local/funcheck/host/funcheck", NULL])
✴ t_list *env={
 ⮡ {SYSTEMD_EXEC_PID=3008},
 ⮡ {SSH_AUTH_SOCK=/run/user/1000/keyring/ssh},
 ⮡ {SESSION_MANAGER=local/altergnu-HP:@/tmp/.ICE-unix/2867,unix/altergnu-HP:/tmp/.ICE-unix/2867},
 ⮡ {GNOME_TERMINAL_SCREEN=/org/gnome/Terminal/screen/3f645528_c6c0_411e_8fc3_0776b2025fa1},
 ⮡ {LANG=en_US.UTF-8},
 ⮡ {XDG_CURRENT_DESKTOP=ubuntu:GNOME},
 ⮡ {PWD=/home/altergnu/Data/shared/42/C3_minishell/Minishell/tests},
 ⮡ {QT_IM_MODULE=ibus},
 ⮡ {GPG_AGENT_INFO=/run/user/1000/gnupg/S.gpg-agent:0:1},
 ⮡ {DESKTOP_SESSION=ubuntu},
 ⮡ {USER=altergnu},
 ⮡ {XDG_MENU_PREFIX=gnome-},
 ⮡ {HOME=/home/altergnu},
 ⮡ {DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus},
 ⮡ {GTK_MODULES=gail:atk-bridge},
 ⮡ {XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/etc/xdg},
 ⮡ {WINDOWPATH=2},
 ⮡ {XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop},
 ⮡ {XDG_SESSION_DESKTOP=ubuntu},
 ⮡ {GSM_SKIP_SSH_AGENT_WORKAROUND=true},
 ⮡ {GNOME_DESKTOP_SESSION_ID=this-is-deprecated},
 ⮡ {QT_ACCESSIBILITY=1},
 ⮡ {DEBUGINFOD_URLS=https://debuginfod.ubuntu.com },
 ⮡ {LOGNAME=altergnu},
 ⮡ {GNOME_TERMINAL_SERVICE=:1.115},
 ⮡ {PATH=/home/altergnu/.local/funcheck/host:/home/altergnu/.local/bin:/home/altergnu/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin:/snap/bin},
 ⮡ {MEMORY_PRESSURE_WRITE=c29tZSAyMDAwMDAgMjAwMDAwMAA=},
 ⮡ {XMODIFIERS=@im=ibus},
 ⮡ {SHELL=/usr/bin/zsh},
 ⮡ {XDG_SESSION_TYPE=x11},
 ⮡ {GNOME_SHELL_SESSION_MODE=ubuntu},
 ⮡ {XDG_RUNTIME_DIR=/run/user/1000},
 ⮡ {USERNAME=altergnu},
 ⮡ {VTE_VERSION=7600},
 ⮡ {MEMORY_PRESSURE_WATCH=/sys/fs/cgroup/user.slice/user-1000.slice/user@1000.service/session.slice/org.gnome.SettingsDaemon.MediaKeys.service/memory.pressure},
 ⮡ {GNOME_KEYRING_CONTROL=/run/user/1000/keyring},
 ⮡ {XAUTHORITY=/run/user/1000/gdm/Xauthority},
 ⮡ {COLORTERM=truecolor},
 ⮡ {DISPLAY=:1},
 ⮡ {TERM=xterm-256color},
 ⮡ {GDMSESSION=ubuntu},
 ⮡ {XDG_SESSION_CLASS=user},
 ⮡ {SHLVL=1},
 ⮡ {OLDPWD=/home/altergnu/Data/shared/42/C3_minishell/Minishell},
 ⮡ {ZSH=/home/altergnu/.oh-my-zsh},
 ⮡ {VIMRC=/home/altergnu/.vim/vimrc},
 ⮡ {CLE=/media/altergnu/Lexar/},
 ⮡ {DOTPATH=/home/altergnu/Projects/Dotfiles},
 ⮡ {PAGER=less},
 ⮡ {LESS=-R},
 ⮡ {LSCOLORS=Gxfxcxdxbxegedabagacad},
 ⮡ {LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=00:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.avif=01;35:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:*~=00;90:*#=00;90:*.bak=00;90:*.crdownload=00;90:*.dpkg-dist=00;90:*.dpkg-new=00;90:*.dpkg-old=00;90:*.dpkg-tmp=00;90:*.old=00;90:*.orig=00;90:*.part=00;90:*.rej=00;90:*.rpmnew=00;90:*.rpmorig=00;90:*.rpmsave=00;90:*.swp=00;90:*.tmp=00;90:*.ucf-dist=00;90:*.ucf-new=00;90:*.ucf-old=00;90:},
 ⮡ {_=/home/altergnu/.local/funcheck/host/funcheck},
 ⮡ NULL }
======================================================================================= ✅

   [33m┌[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m┐[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   [33mfuncheck[0m -- [1m1.1.4[0m             [33m│[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   - program: [1m./bin/test_build_env_lst[0m     [33m│[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   - arguments:                  [33m│[0m
   [33m└[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m┘[0m

[44m[1m INFO [0m If your program wait for stdin input, you can type here or pipe it.
[33m───────────── TTY ────────────[0m
[33m──────────────────────────────[0m
[46m[1m TASK [0m Testable functions fetching [42m[1m ✓ [0m
[44m[1m INFO [0m Functions detected count: [1m115[0m


[1mFunction tests: [32m115 passed[0m, 115 in total
[1mTime:[0m           1 min 42 sec
[1mSuccess rate:[0m   100 %
[0;37mAll tests ran[0m
