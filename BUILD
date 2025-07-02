cc_library(
    name = "lexer",
    srcs = ["src/lexer.cpp"],
    hdrs = ["src/lexer.h"],
    includes = ["src"],
    visibility = ["//visibility:public"],
)

cc_test(
    name = "lexer_test",
    testonly = True,
    srcs = ["tests/lexer.cpp"],
    includes = ["src"],
    deps = [
        ":lexer",
        "@googletest//:gtest_main",
    ],
)
