#include "SettingsDialog.h"

SettingsDialog::SettingsDialog(QWidget* parent)
    : QDialog(parent)
{

    ui.setupUi(this);
    QObject::connect(ui.slowPlayerSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
                     &SettingsDialog::onSlowPlayerSpinboxChanged);
    QObject::connect(ui.mediumPlayerSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
                     &SettingsDialog::onMediumPlayerSpinBoxChanged);
    QObject::connect(ui.fastPlayerSpinBox, qOverload<int>(&QSpinBox::valueChanged), this,
                     &SettingsDialog::onFastPlayerSpinBoxChanged);
}

void SettingsDialog::setSlowPlayerSpinBox(unsigned int value)
{
    ui.slowPlayerSpinBox->setValue(static_cast<int>(value));
}

void SettingsDialog::setMediumPlayerSpinBox(unsigned int value)
{
    ui.mediumPlayerSpinBox->setValue(static_cast<int>(value));
}

void SettingsDialog::setFastPlayerSpinBox(unsigned int value)
{
    ui.fastPlayerSpinBox->setValue(static_cast<int>(value));
}
