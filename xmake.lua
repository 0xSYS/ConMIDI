add_rules("mode.debug", "mode.release")

target("ConMIDI")
    set_kind("binary")
    -- add_shflags("-pthread")
    add_files("src/**.c")
    add_links("ncurses", "pthread")
