#!/usr/bin/python3

"""
Para correr esta script é necessário:
- Instalar o multimetric
- Instalar o tabulate
- Copiar esta script para um local onde esteja acessível, por exemplo ~/.local/bin ou /usr/local/bin
- Alterar as permissões para a script ser executável
# Instalação do que é necessário
pip3 install multimetric
pip3 install tabulate
# Legenda
LoC
 : lines of code
CC
 : complexidade ciclomática (deve estar abaixo de 10)
MI
 : índece de capacidade de manutenção (deve estar acima de 80)
Comments
 : percentagem de código que corresponde a comentários
"""

import subprocess
import sys
import os
import json
import pprint
import tabulate

assert len(sys.argv) == 2, "Usage: {sys.argv[0]} directory"
dir = sys.argv[1]
assert os.path.isdir(dir), f"{dir} is not a directory!"

legend = dict(comment_ratio = "Comments", cyclomatic_complexity = "CC", maintainability_index = "MI", loc = "LoC")
res = json.loads(subprocess.getoutput(f"multimetric {dir}/*.c"))

overall = {v : res['overall'][k] for k, v in legend.items()}
overall['file'] = 'overall'
tab = []

for file in sorted(res['files']):
    entry = {'file' : file}
    entry.update({v : res['files'][file].get(k) for k, v in legend.items()})
    tab.append(entry)
tab.append(overall)

print(tabulate.tabulate(tab, headers = "keys"))
print()

cc_max = 10
cc_min = 50
mi_max = 80
mi_min = 40

cc = (cc_min - max(cc_max, overall['CC'])) / (cc_min - cc_max)
mi = (min(mi_max, overall['MI']) - mi_min) / (mi_max - mi_min)

print(f"Nota Legibilidade = {50 * cc + 50 * mi : .2f}%")
print("""Disclaimer: esta nota é meramente indicativa e só se pode confiar se:
- se se estiver a correr a última versão desta script, e
- se possuir a mesma versão de todos os pacotes que a máquina virtual, e
- se correu a script em Linux
""")