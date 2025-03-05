add_rules("mode.debug", "mode.release")

target("ConMIDI")
    set_kind("binary")
    add_files("src/**.c")