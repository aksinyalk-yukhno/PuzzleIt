#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QPushButton>
#include <QPropertyAnimation>

class CustomButton : public QPushButton
{
    Q_OBJECT
public:
    CustomButton(const QString &text, QWidget *parent = nullptr) : QPushButton(text, parent) {}

protected:
    void enterEvent(QEvent *) override
    {
        // Add animation when mouse enters the button
        setProperty("hover", true);
        QPropertyAnimation *animation = new QPropertyAnimation(this, "minimumWidth");
        animation->setDuration(200);
        animation->setStartValue(minimumWidth());
        animation->setEndValue(250);
        animation->start();
    }

    void leaveEvent(QEvent *) override
    {
        // Add animation when mouse leaves the button
        setProperty("hover", false);
        QPropertyAnimation *animation = new QPropertyAnimation(this, "minimumWidth");
        animation->setDuration(200);
        animation->setStartValue(minimumWidth());
        animation->setEndValue(50);
        animation->start();
    }
};

#endif // CUSTOMBUTTON_H
