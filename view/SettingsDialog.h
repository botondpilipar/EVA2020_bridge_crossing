#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "ui_settings.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    SettingsDialog(QWidget* parent = nullptr);
    void setSlowPlayerSpinBox(unsigned int );
    void setMediumPlayerSpinBox(unsigned int );
    void setFastPlayerSpinBox(unsigned int);

    inline unsigned int getSelectedSlowPlayerNumber() { return mSlowPlayerNumberSelected; }
    inline unsigned int getSelectedMediumPlayerNumber() {return mMediumPlayerNumberSelected; }
    inline unsigned int getSelectedFastPlayerNumber() { return mFastPlayerNumberSelected; }

protected slots:
    void onSlowPlayerSpinboxChanged(int value) { mSlowPlayerNumberSelected = static_cast<unsigned>(value); }
    void onMediumPlayerSpinBoxChanged(int value) { mMediumPlayerNumberSelected = static_cast<unsigned>(value); }
    void onFastPlayerSpinBoxChanged(int value) { mFastPlayerNumberSelected = static_cast<unsigned>(value); }
private:
    Ui::SettingsDialog ui;
    unsigned int mSlowPlayerNumberSelected;
    unsigned int mMediumPlayerNumberSelected;
    unsigned int mFastPlayerNumberSelected;

};

#endif // SETTINGSDIALOG_H
