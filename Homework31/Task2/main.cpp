#include <QApplication>
#include <QWidget>
#include <QPlainTextEdit>
#include <QTextBrowser>
#include <QHBoxLayout>
#include <QSizePolicy>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // 1. главное окно
    QWidget mainWindow;
    mainWindow.setWindowTitle("Wysiwyg_editor");
    mainWindow.resize(1000, 600); // стартовый размер

    // 2. Текстовый редактор для кода и просмотрщик
    QPlainTextEdit *sourceEditor = new QPlainTextEdit(&mainWindow);
    QTextBrowser *resultedView = new QTextBrowser(&mainWindow);

    // 3. одинаковые пропорции растяжения
    QSizePolicy policy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    policy.setHorizontalStretch(1);

    sourceEditor->setSizePolicy(policy);
    resultedView->setSizePolicy(policy);

    // 4. Добавляем в горизонтальный компоновщик
    QHBoxLayout *layout = new QHBoxLayout(&mainWindow);
    layout->addWidget(sourceEditor);
    layout->addWidget(resultedView);
    mainWindow.setLayout(layout);

    // 5. Начальный HTML-текст для демонстрации
    QString defaultHtml =
        "<html>\n"
        "<head>\n"
        "  <meta charset=\"utf-8\">\n"
        "  <title>Hello skillbox</title>\n"
        "</head>\n"
        "<body>\n"
        "  <h1>Hello, wysiwyg editor!</h1>\n"
        "  <h2>Skillbox</h2>\n"
        "  <p>Text example</p>\n"
        "  <ul>\n"
        "    <li>param 1</li>\n"
        "    <li>param 2</li>\n"
        "    <li>param 3</li>\n"
        "  </ul>\n"
        "</body>\n"
        "</html>";

    sourceEditor->setPlainText(defaultHtml);
    resultedView->setHtml(defaultHtml);

    // 6. Связываем левое поле с правым: мгновенное обновление при вводе
    QObject::connect(sourceEditor, &QPlainTextEdit::textChanged, [sourceEditor, resultedView]() {
        QString currentCode = sourceEditor->toPlainText();
        resultedView->setHtml(currentCode);
    });

    mainWindow.show();
    return app.exec();
}
