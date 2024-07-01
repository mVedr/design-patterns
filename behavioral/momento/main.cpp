#include <iostream>
#include <string>

class Editor;

class Snapshot {
public:
    Snapshot(Editor* editor, const std::string& text, int curX, int curY, int selectionWidth);

    void restore();

private:
    Editor* editor;
    std::string text;
    int curX, curY, selectionWidth;
};

class Editor {
public:
    void setText(const std::string& text) {
        this->text = text;
    }

    void setCursor(int x, int y) {
        this->curX = x;
        this->curY = y;
    }

    void setSelectionWidth(int width) {
        this->selectionWidth = width;
    }

    Snapshot* createSnapshot() {
        return new Snapshot(this, text, curX, curY, selectionWidth);
    }

    void printState() const {
        std::cout << "Text: " << text << ", Cursor: (" << curX << ", " << curY << "), Selection Width: " << selectionWidth << std::endl;
    }

private:
    std::string text;
    int curX, curY, selectionWidth;
};

Snapshot::Snapshot(Editor* editor, const std::string& text, int curX, int curY, int selectionWidth)
    : editor(editor), text(text), curX(curX), curY(curY), selectionWidth(selectionWidth) {}

void Snapshot::restore() {
    editor->setText(text);
    editor->setCursor(curX, curY);
    editor->setSelectionWidth(selectionWidth);
}

class Command {
public:
    Command(Editor* editor) : editor(editor), backup(nullptr) {}

    ~Command() {
        delete backup;
    }

    void makeBackup() {
        delete backup; 
        backup = editor->createSnapshot();
    }

    void undo() {
        if (backup != nullptr) {
            backup->restore();
        }
    }

private:
    Editor* editor;
    Snapshot* backup;
};

int main() {
    Editor editor;
    Command command(&editor);

    editor.setText("Hello, World!");
    editor.setCursor(10, 20);
    editor.setSelectionWidth(5);
    editor.printState();

    // Making a backup
    command.makeBackup();

    // Changing the state
    editor.setText("New Text");
    editor.setCursor(30, 40);
    editor.setSelectionWidth(10);
    editor.printState();

    // Undo changes
    command.undo();
    editor.printState();

    return 0;
}
