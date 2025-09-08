# ni $PWD/main.cpp

$content = "#include <iostream>`n" +
            "#include <fstream>`n" +
            "#include <sstream> `n" +
            "#include <vector>`n" +
            "`nusing namespace std;`n" +
            "`nint main(void) {`n" +
            "`tifstream in(`"input.txt`");`n" +
            "`tstring line;`n" +
            "`twhile(getline(in, line)) `{`n" +
            "`t`tcout << line << '\n';`n" +
            "`t}`n" +
            "}"

Set-Content -Path $PWD/main.cpp -Value $content
