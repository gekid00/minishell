#!/bin/bash

# ===================================================================
# VALIDATION RAPIDE MINISHELL - 42 SCHOOL
# Script optimisé sans timeout pour l'évaluation
# ===================================================================

GREEN='\033[0;32m'
RED='\033[0;31m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo "╔══════════════════════════════════════════════════════════════════════════════╗"
echo "║                    VALIDATION RAPIDE MINISHELL - 42 SCHOOL                  ║"
echo "╚══════════════════════════════════════════════════════════════════════════════╝"
echo ""

TOTAL_TESTS=0
PASSED_TESTS=0

# Test de compilation
echo -e "${BLUE}🔧 COMPILATION${NC}"
echo "────────────────"
echo -n "├─ Test compilation... "
if make > /dev/null 2>&1; then
    echo -e "${GREEN}✅ PASSED${NC}"
    ((PASSED_TESTS++))
else
    echo -e "${RED}❌ FAILED${NC}"
fi
((TOTAL_TESTS++))

# Test fonctionnel de base
echo ""
echo -e "${BLUE}⚙️ FONCTIONNALITÉS DE BASE${NC}"
echo "─────────────────────────────"
echo -n "├─ Test echo... "
if echo -e "echo hello\nexit" | ./minishell 2>/dev/null | grep -q "hello"; then
    echo -e "${GREEN}✅ PASSED${NC}"
    ((PASSED_TESTS++))
else
    echo -e "${RED}❌ FAILED${NC}"
fi
((TOTAL_TESTS++))

echo -n "├─ Test pipes... "
if echo -e "echo hello | cat\nexit" | ./minishell 2>/dev/null | grep -q "hello"; then
    echo -e "${GREEN}✅ PASSED${NC}"
    ((PASSED_TESTS++))
else
    echo -e "${RED}❌ FAILED${NC}"
fi
((TOTAL_TESTS++))

echo -n "├─ Test redirections... "
if echo -e "echo test > /tmp/minishell_test.txt\nexit" | ./minishell > /dev/null 2>&1 && [ -f /tmp/minishell_test.txt ] && grep -q "test" /tmp/minishell_test.txt; then
    echo -e "${GREEN}✅ PASSED${NC}"
    ((PASSED_TESTS++))
    rm -f /tmp/minishell_test.txt
else
    echo -e "${RED}❌ FAILED${NC}"
    rm -f /tmp/minishell_test.txt
fi
((TOTAL_TESTS++))

echo -n "├─ Test variables... "
if echo -e "export TEST=value\necho \$TEST\nexit" | ./minishell 2>/dev/null | grep -q "value"; then
    echo -e "${GREEN}✅ PASSED${NC}"
    ((PASSED_TESTS++))
else
    echo -e "${RED}❌ FAILED${NC}"
fi
((TOTAL_TESTS++))

# Tests mémoire
echo ""
echo -e "${BLUE}🧪 TESTS MÉMOIRE (VALGRIND)${NC}"
echo "────────────────────────────────"

echo -n "├─ Test fuites basique... "
VALGRIND_OUTPUT=$(echo -e "echo hello\nexit" | valgrind --leak-check=full --show-leak-kinds=definite --suppressions=readline.supp --error-exitcode=42 ./minishell 2>&1)
if echo "$VALGRIND_OUTPUT" | grep -q "definitely lost: 0 bytes"; then
    echo -e "${GREEN}✅ NO LEAKS${NC}"
    ((PASSED_TESTS++))
else
    echo -e "${RED}❌ LEAKS DETECTED${NC}"
fi
((TOTAL_TESTS++))

echo -n "├─ Test fuites pipes... "
VALGRIND_OUTPUT=$(echo -e "echo test | cat\nexit" | valgrind --leak-check=full --show-leak-kinds=definite --suppressions=readline.supp --error-exitcode=42 ./minishell 2>&1)
if echo "$VALGRIND_OUTPUT" | grep -q "definitely lost: 0 bytes"; then
    echo -e "${GREEN}✅ NO LEAKS${NC}"
    ((PASSED_TESTS++))
else
    echo -e "${RED}❌ LEAKS DETECTED${NC}"
fi
((TOTAL_TESTS++))

# Résultats finaux
echo ""
echo "═══════════════════════════════════════════════════════════════════════════════"
echo -e "${BLUE}📊 RÉSULTATS FINAUX${NC}"
echo "═══════════════════════════════════════════════════════════════════════════════"

PERCENTAGE=$((PASSED_TESTS * 100 / TOTAL_TESTS))
echo -e "🎯 ${BLUE}TESTS RÉUSSIS: ${PASSED_TESTS}/${TOTAL_TESTS} (${PERCENTAGE}%)${NC}"

if [ $PASSED_TESTS -eq $TOTAL_TESTS ]; then
    echo ""
    echo -e "${GREEN}🎉 FÉLICITATIONS ! 🎉${NC}"
    echo "╔══════════════════════════════════════════════════════════════════════════════╗"
    echo -e "║ ${GREEN} MINISHELL PRÊT POUR L'ÉVALUATION 42 SCHOOL !${NC}                         ║"
    echo "║                                                                              ║"
    echo -e "║  ${GREEN}✅ Compilation parfaite${NC}                                               ║"
    echo -e "║  ${GREEN}✅ Toutes les fonctionnalités testées${NC}                                 ║"
    echo -e "║  ${GREEN}✅ Aucune fuite mémoire détectée${NC}                                      ║"
    echo -e "║  ${GREEN}✅ Prêt pour la défense !${NC}                                             ║"
    echo "╚══════════════════════════════════════════════════════════════════════════════╝"
else
    echo ""
    echo -e "${RED}⚠️  ATTENTION: Certains tests ont échoué${NC}"
    echo "Veuillez corriger les problèmes avant l'évaluation."
fi

echo ""
echo "═══════════════════════════════════════════════════════════════════════════════"
echo "Validation terminée le: $(date)"
echo "═══════════════════════════════════════════════════════════════════════════════"
