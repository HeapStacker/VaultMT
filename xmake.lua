set_version("1.0.0")

package("vault")
    set_homepage("https://github.com/HeapStacker/Vault")
    set_description("Type-safe owning container with polymorphic clone support")
    set_license("MIT")

    add_urls("https://github.com/HeapStacker/Vault/archive/refs/tags/v$(version).tar.gz",
             "https://github.com/HeapStacker/Vault.git")
    add_versions("1.0.0", "9d37ad981494690252ce781290028e38b9ce348b")

    add_deps("exporter")

    on_install(function (package)
        import("package.tools.xmake").install(package)
    end)

    on_test(function (package)
        assert(package:has_cincludes("vault/Container.hpp", {configs = {languages = "c++20"}}))
    end)
package_end()

target("vault")
    set_kind("headeronly")
    add_headerfiles("include/(**.hpp)")
    add_includedirs("include", {public = true})
    add_packages("exporter", {public = true})
target_end()
