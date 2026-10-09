local projectName = tostring(os.getenv("PIXI_PROJECT_NAME"))
local projectVersion = os.getenv("PIXI_PROJECT_VERSION")

set_project(projectName)
set_version(projectVersion)
set_languages("c++23")

add_rules("mode.debug", "mode.release")
set_warnings("all", "error")

add_rules("plugin.compile_commands.autoupdate", { outputdir = "." })

if is_plat("windows", "mingw") and not is_config("build_android") then
    set_toolchains("msvc")
    add_defines("WIN32_LEAN_AND_MEAN", "NOMINMAX")
    add_cxflags("/utf-8", "/Zc:__cplusplus")
end

target("vault")
    set_kind("headeronly")
    add_headerfiles("include/(**.hpp)")
    add_includedirs("include", {public = true})
    add_packages("exporter", "logger", {public = true})
target_end()
