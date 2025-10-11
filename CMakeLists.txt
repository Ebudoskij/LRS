cmake_minimum_required(VERSION 3.10)
project(PerformanceExperiments CXX)

# Встановлюємо стандарт C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# --- ВИПРАВЛЕННЯ: Заміна GCC прапорців на MSVC еквіваленти ---
# /W3: Рівень попереджень, еквівалентний -Wall
# /wd4251: Ігноруємо поширене попередження MSVC, не пов'язане з продуктивністю
add_compile_options(/W3 /wd4251) 

# Всі експерименти потребують цих файлів
set(ALL_COMMON_SOURCES
    LoggerCSV.cpp
    Accumulate.cpp
    Generator.cpp
)
# ------------------------------------------------------------------

# 1. Експеримент: DataRange.cpp (std::min_element vs Volume)
add_executable(Experiment1
    ${ALL_COMMON_SOURCES}
    Executables/DataRange.cpp
)
target_compile_options(Experiment1 PRIVATE /O2) # /O2 = O2 для MSVC
set_target_properties(Experiment1 PROPERTIES 
    RUNTIME_OUTPUT_NAME "run_exp1_o2"
)

# 2. Експеримент: ThreadAmount.cpp (MultiThread vs Threads)
add_executable(Experiment2
    ${ALL_COMMON_SOURCES}
    Executables/ThreadAmount.cpp
)
target_compile_options(Experiment2 PRIVATE /O2)
set_target_properties(Experiment2 PROPERTIES 
    RUNTIME_OUTPUT_NAME "run_exp2_o2"
)

# 3. Експеримент: Optimization (Три цілі з різною оптимізацією)

# 3a. O0
add_executable(Experiment3_O0 
    ${ALL_COMMON_SOURCES}
    Executables/RunningPolicies.cpp
)
target_compile_options(Experiment3_O0 PRIVATE /Od) # /Od = O0 для MSVC
set_target_properties(Experiment3_O0 PROPERTIES 
    RUNTIME_OUTPUT_NAME "run_exp3_o0"
)

# 3b. O2
add_executable(Experiment3_O2 
    ${ALL_COMMON_SOURCES}
    Executables/RunningPolicies.cpp
)
target_compile_options(Experiment3_O2 PRIVATE /O2)
set_target_properties(Experiment3_O2 PROPERTIES 
    RUNTIME_OUTPUT_NAME "run_exp3_o2"
)

# 3c. O3
add_executable(Experiment3_O3 
    ${ALL_COMMON_SOURCES}
    Executables/RunningPolicies.cpp
)
target_compile_options(Experiment3_O3 PRIVATE /O3) # /O3 = O3 для MSVC
set_target_properties(Experiment3_O3 PROPERTIES 
    RUNTIME_OUTPUT_NAME "run_exp3_o3"
)