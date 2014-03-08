message(STATUS "generating translations")
find_package(Qt5LinguistTools REQUIRED)

set(LANGS
	language_de.ts
	language_en.ts
)

qt5_add_translation(TRANSLATIONS language_de.ts language_en.ts)
