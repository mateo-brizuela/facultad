#!/bin/bash
# Script de auditoría básica TP5 - Auditoría Informática (IUA)
# Autor: Mauro Brizuela
# Fecha: $(date)

OUT="auditoria_sistema.txt"
echo "AUDITORÍA DEL EQUIPO - TP5 IUA" > $OUT
echo "Fecha: $(date)" >> $OUT
echo "--------------------------------------------" >> $OUT

echo -e "\n1. LICENCIAS DE SOFTWARE" >> $OUT
dpkg -l | awk '{print $2}' | head -n 20 >> $OUT
echo -e "\n(Ejemplo: Chrome, VSCode, Zoom son propietarios)" >> $OUT

echo -e "\n2. PROTECCIÓN ANTI-MALWARE" >> $OUT
if command -v clamscan &> /dev/null; then
  clamscan --version >> $OUT
  echo "ClamAV instalado y operativo." >> $OUT
else
  echo "ClamAV no instalado. Instalar con: sudo apt install clamav" >> $OUT
fi

echo -e "\n3. FIREWALL (UFW)" >> $OUT
sudo ufw status verbose >> $OUT

echo -e "\n4. SOFTWARE SOSPECHOSO INSTALADO" >> $OUT
dpkg -l | grep -Ei "hack|torrent|bitcoin|crack" >> $OUT || echo "No se detecta software sospechoso." >> $OUT

echo -e "\n5. USUARIOS DEL SISTEMA Y GRUPOS" >> $OUT
echo -e "\nUsuarios:" >> $OUT
cut -d: -f1 /etc/passwd | head -n 15 >> $OUT
echo -e "\nGrupos:" >> $OUT
cut -d: -f1 /etc/group | head -n 15 >> $OUT

echo -e "\n6. LOGS DE EVENTOS (últimos errores críticos)" >> $OUT
sudo journalctl -p 3 -xb | head -n 30 >> $OUT

echo -e "\n7. SUPUESTOS Y OBSERVACIONES" >> $OUT
echo "Equipo personal sin software corporativo. Antivirus ClamAV considerado suficiente." >> $OUT
echo "No se auditan licencias de drivers propietarios ni firmware." >> $OUT

echo -e "\n--------------------------------------------" >> $OUT
echo "FIN DE AUDITORÍA" >> $OUT

cat $OUT
