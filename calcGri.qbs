import qbs

CppApplication {
    consoleApplication: true
    files: [
        "MAINcalculator.cpp",
        "calculate.cpp",
        "calculate.h",
        "std_lib_facilities.h",
        "token.cpp",
        "token.h",
        "variable.cpp",
        "variable.h",
    ]

    Group {     // Properties for the produced executable
        fileTagsFilter: "application"
        qbs.install: true
        qbs.installDir: "bin"
    }
}
